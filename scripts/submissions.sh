#!/usr/bin/env bash

base=~/checking/current # use ln -s

static_dir=$base
instance_dir=$base/instance

assignment=$static_dir/assn-files
data=$assignment/data
zip_location=$static_dir/zips # it was zip for assn1 I think

checking_dir=$instance_dir/checking
submissiondir=$instance_dir/submissions
failed_dir=$instance_dir/failed
status_dir=$instance_dir/status
current_status=$instance_dir/current
logs_file=$instance_dir/logs

source $static_dir/assn-info.sh
# assn 1


terminal=kitty
function main() {
    load
    create_status_files
    open_cp
    unzip_all
    clean_all
    init
    check_all
    evaluate_all
}
function getSubmissionZips() {
    ls -1v $zip_location/*.zip
}

submissions=($(getSubmissionZips | xargs -I {} basename {} .zip))
echo $submissions

function move() {
    log basename $(pwd): moving files from $1
    cp -r $1/* .
    rm -r $1
}

# not improving this since won't be necessary with proper submissions
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
                    # or just use find, jfc
                    log $submission: no solution found
                    log $(ls -1v)
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

function clean_all() {
    for submission in "${submissions[@]}"
    do
        cd $submissiondir/$submission
        # poor logic for checking correct directory structure
        file=$(ls $main_file)
        if [ ! -f "$file" ]
        then
            while [ -z "$file" ]
            do
                log "cleaning $submission"
                clean $submission
                # in other cases, mv submission failed instead of clean
                # and no while loop
                file=$(ls $main_file)
            done
            echo "$submission required cleaning" > $static_dir/problems
        fi
        update_status $submission "cleaned"
    done
}

function log() {
    msg="$1"
    echo "\t\t\t$msg" | tee $current_status
    echo $msg >> $logs_file
}

function unzip_one() {
    submission=$1
    output=$2
    mkdir $output
    unzip -q $zip_location/$submission.zip -d $output
}

function unzip_all() {
#    if [[ -d $submissiondir ]]
#    then
#        # this should change what if I added just one zip
#        log "skipping unzip"
#    else
        mkdir $submissiondir
        log "starting unzip.."
        for submission in "${submissions[@]}"
        do
            output=$submissiondir/$submission
            if [ -d $output ]
            then
                log "$submission: skipped"
            else
                log "unzipping $submission to $output"
                unzip_one $submission $output
                update_status $submission "unzipped"
            fi
        done
        echo "all submissions unzipped"
#    fi

}

function count() {
    # assn 1 for each test, 3 version checks + 1 memory check
    # kewyord="SUCCESSED"
    # assn 4
    keyword="SUCCESSFULY"
    cat $1 | grep $keyword | wc -l
}

# assignment 4


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
    # cp -r $data . # needed for assignment 1
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
            log "$submission: already built"
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
        if [[ -f $submission/$target ]]
        then
            [[ -f $submission/results.txt ]] && log "$submission: already checked" || check $submission
        else
            echo "$submission,failed,failed" >> $submission/results_final.txt
            update_status $submission "failed"
        fi
    done
}

function evaluate_all() {
    for submission in "${submissions[@]}"
    do
        cd $checking_dir
        result=$submission/results_final.txt
        [[ -f $result ]] && cat $result >> $static_dir/final.txt
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
function status() {
    cat $statid_dir/status_header $status_dir/* | less
}

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
    message=$2
    msg="$submission: $message"
    file=$status_dir/$submission
    already_logged=$(grep $message $file)
    if [ -z "$already_logged" ]
    then
        echo -n $(tr -d '\n' < $file) > $file
        echo "\t$message" >> $file
    fi
    log $msg
}

function load() {
    source ~/scripts/submissions
}

function cleanup() {
    rm -rf $instance_dir
}

function open_cp() {
    $terminal watch -t check_status $static_dir $status_dir &
}

