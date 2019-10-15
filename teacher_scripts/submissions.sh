#!/usr/bin/env bash

submissiondir=~/submissions
function getSubmissionZips {
    ls -1v ~/Downloads/???????.zip
}

function getStudentId {
    basename $1 .zip
}
submissions=($(getSubmissionZips | xargs -I {} basename {} .zip))
echo $submissions
function unzip() {
    for submission in "${submissions[@]}"
    do
        output=~/submissions/$submission
        mkdir $output
        unzip ~/Downloads/$submission.zip -d $output
    done
}

function move() {
    echo basename $(pwd): moving files from $1
    cp -r $1/* .
    rm -r $1
}
function cleanup() {
    for submission in "${submissions[@]}"
    do
        cd $submissiondir/$submission
        file=$(ls rsg.cc)
        if [ -z "$file" ]
        then
            file=$(ls assn-1-rsg)
            if [ -z "$file" ]
            then
                file=$(ls ass1)
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
                    move assn1
                fi
            else
                move assn-1-rsg
            fi
        else
            echo $submission: file exists
        fi
    done
}


assignment=~/assn-1-rsg
data=~/data

function check() {
    checkers=($(/bin/ls -1v data))
    for checker in "${checkers[@]}"
    do
        echo "\n*****$checker*****\n" >> results
        ./rsgChecker ./rsg ./data/$checker >> results
    done
    echo "finished checking $submission"
    mv results results.txt
}

function initialize() {
    submission=$1
    echo "starting $submission"
    cd $submissiondir/$submission
    cp -nf $assignment/Makefile .
    make clean > /dev/null
    rm -rf data
    rm -rf assn-1-rsg-data
    cp -r $assignment ~/checking/$submission
    cd ~/checking/$submission
    git init > /dev/null
    git add . && git commit -m "initial commit" > /dev/null
    # bin because otherwise it won't overwrite
    /bin/cp -rf $submissiondir/$submission/* .
    cp -r $data .
    make > /dev/null
    echo " finished copy/builidng $submission, ready for checking"
}

function init() {
    cd
    # mkdir checking
    for submission in "${submissions[@]}"
    do
        initialize $submission
        check $submission &
    done
}
