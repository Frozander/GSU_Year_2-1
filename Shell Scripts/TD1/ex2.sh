#!/bin/bash
file_list=`ls -l`

for entry in $file_list
do
    if test -f $entry
    then
        if test "`head -1 $entry`" = "#!/bin/bash"
        then
            echo "$entry is a script"
        fi
    fi
done