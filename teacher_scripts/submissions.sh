#!/usr/bin/env bash

base=~/checked3
submissiondir=$base/submissions
checking_dir=$base/checking
zip_location=$base/zips

function getSubmissionZips() {
    ls -1v $zip_location/???????.zip
}

function move() {
    echo basename $(pwd): moving files from $1
    cp -r $1/* .
    rm -r $1
}

# not improving this since won't be necessary with proper submissions
assn_name=ass1
assn_alt=assn-1-rsg
function clean() {
    submission=$1
    file=$(ls $main_file)
        file=$(ls $assn_alt)
        if [ -z "$file" ]
        then
            file=$(ls $assn_name)
            if [ -z "$file" ]
            then
                file=$(ls $submission)
                if [ -z "$file" ]
                then
                    # new scenarios would be nested here
                    echo $submission: no solution found
                    echo $(ls -1v)
                else
                    move $submission
                fi
            else
                move $assn_name
            fi
        else
            move $assn_alt
        fi
}

main_file=rsg.cc
function cleanup() {
    for submission in "${submissions[@]}"
    do
        cd $submissiondir/$submission
        # poor logic for checking correct directory structure
        file=$(ls $main_file)
        if [ -f "$file" ]
        then
            log "$submission already cleaned"
        else
            while [ -z "$file" ]
            do
                log "cleaning $submission"
                clean $submission
                # in other cases, mv submission failed instead of clean
                # and no while loop
                file=$(ls $main_file)
            done
        fi
        update_status $submission "cleaned"
    done
}

function log() {
    msg="$1"
    echo "\t\t\t$msg" | tee $base/current
    echo $msg >> logs
}
function unzip_one() {
    submission=$1
    output=$2
    mkdir $output
    unzip -q $zip_location/$submission.zip -d $output
}

submissions=($(getSubmissionZips | xargs -I {} basename {} .zip))
echo $submissions
function unzip_all() {
    if [[ -d $submissiondir ]]
    then
        echo "skipping unzip"
    else
        mkdir $submissiondir
        echo "starting unzip.."
        for submission in "${submissions[@]}"
        do
            output=$submissiondir/$submission
            if [ -d $output ]
            then
                echo "$submission: skipped"
            else
                log "unzipping $submission"
                unzip_one $submission $output
                update_status $submission "unzipped"
            fi
        done
        echo "all submissions unzipped"
    fi

}



assignment=~/assn-1-rsg
data=~/data
function count() {
    # for each test, 3 version checks + 1 memory check
    cat $1 | grep "SUCCESSED" | wc -l
}
function check() {
    submission=$1
    echo "checking $submission"
    cd $checking_dir/$submission
    rm -f results results_extra results.txt results_extra.txt
    checkers=($(/bin/ls -1v data))
    base_checkers=(excuse.g bond.g trek.g poem.g)
    for checker in "${checkers[@]}"
    do
        echo -n "\t$checker: "
        results=results_extra
        case "${base_checkers[@]}" in *$checker*) results=results ;; esac
        echo "\n*****$checker*****\n" >> $results
        ./rsgChecker ./rsg ./data/$checker >> $results
        echo "done"
    done
    update_status $submission "checked"
    results_base=$(count results)
    results_extra=$(count results_extra)
    echo "$submission,$results_base,$results_extra" >> results_final.txt
    mv results_extra results_extra.txt
    mv results results.txt # can check if finalized using this
}

function initialize() {
    submission=$1
    cd $submissiondir/$submission
    cp -nf $assignment/Makefile .
    make clean > /dev/null
    rm -rf data
    rm -rf assn-1-rsg-data
    cp -r $assignment $checking_dir/$submission
    cd $checking_dir/$submission
    git init > /dev/null
    git add . && git commit -m "initial commit" > /dev/null
    # bin because otherwise it won't overwrite
    /bin/cp -rf $submissiondir/$submission/* .
    cp -r $data .
    make > compile-logs.txt 2> compile-errors.txt && update_status $submission "built" &
}
# [[ -s $i/compile-errors.txt ]] && echo "$i: error" || echo "$i: no error"
#
function init() {
    cd
    mkdir -p $checking_dir
    for submission in "${submissions[@]}"
    do
        if [ -f $checking_dir/$submission/compile-logs.txt ]
        then
            echo "$submission: already built"
        else
            log "building $submission"
            initialize $submission
        fi
    done
}

function check_all() {
    for submission in "${submissions[@]}"
    do
        cd $checking_dir
        if [[ -f $submission/rsg ]]
        then
            [[ -f $submission/results.txt ]] && echo "$submission: already checked" || check $submission
        else
            mv $submission ~/failed/ &
        fi
    done
}

function evaluate_all() {
    for submission in "${submissions[@]}"
    do
        cd $checking_dir
        cat $submission/results_final.txt >> final.txt
    done
}

emacs_view_command_file=~/freeuni/paradigms/teacher_scripts/see-submission.el
function view_submission() {
    submission=$1
    cd $checking_dir/$submission
    view
}

function view() {
    emacsclient -c -e "(load-file \"$emacs_view_command_file\")"
}
status_dir=$base/status
function status() {
    cat $base/status_header $status_dir/* | less
}
terminal=kitty

function create_status_files() {
    mkdir -p $status_dir
    for submission in "${submissions[@]}"
    do
        file=$status_dir/$submission
        [[ -f $file ]] || echo "$submission" >> $file
    done
}

function update_status() {
    submission=$1
    file=$status_dir/$submission
    echo -n $(tr -d '\n' < $file) > $file
    msg="$submission: $2"
    log $msg
    echo "\t$2" >> $file
}

function load() {
    source ~/scripts/submissions
}
function all() {
    create_status_files
    $terminal watch -t check_status $base $status_dir &
    unzip_all
    cleanup
    init
    check_all
    evaluate_all
}
