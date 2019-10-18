#!/bin/bash

file_list=`ls -l`
count=0
folder=0
empty=0

for entry in $file_list
do
    if test -f $entry
    then
        if test "`head -1 $entry`" = "#!/bin/bash"
        then
            let count++
            echo "$entry is a script"
            
        fi
    fi
done

echo "There are $count scripts, $empty are empty"
