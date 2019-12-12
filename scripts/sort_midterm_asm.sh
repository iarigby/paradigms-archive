#!/usr/bin/env bash

base=~/checking/paradigms/midterm_2
works_dir=$base/works
results_dir=$base/results
empty_dir=$base/empty

mkdir -p $results_dir
function collect_works() {
    works=$(/bin/ls $works_dir)
    problem=$1
    for student in ${works[@]}; do
        location=$works_dir/$student
        cd $location
        file=$(fd $problem.s)
        dir=$results_dir/$student
        if [ ! -z "$file" && ! -d $dir ]
        then
            mkdir -p $dir
            cp $file $dir
        fi
    done
}

# collect_works database
# collect_works server_room
function filter_empty() {
    works=$(/bin/ls $results_dir)
    solution_dir=~/freeuni/paradigms/problem_ideas/problems
    problem=$1
    solution=$solution_dir/asm_$problem/$problem.s
    cd $results_dir
    for student in ${works[@]}; do
        file=$(fd $problem.s $student)
        if [ ! -z "$file" ]
        then
            changed_something=$(diff $student/$problem.s $solution)
            if [ -z "$changed_something" ]
            then # nothing was changed
                echo "will move $student to failed"
                mv $student $empty_dir
            fi
        fi
    done
}

filter_empty database
filter_empty server_room
