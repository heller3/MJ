#!/bin/bash

INPUTDIR=/net/cms26/cms26r0/jaehyeok
DATASET=$1
RECOGNIZER=$2
ISDATA=$3
LUMI=$4
NFILEPERJOB=$5

# make an output dir 
#if [ ! -d "$OUTPUTDIR/$DATASET/slim" ] 
#then 
#    echo " [DEBUG] Making directory $OUTPUTDIR/$DATASET/slim " 
#    mkdir -p $OUTPUTDIR/$DATASET/slim 
#fi 

#### cleaning  
rm filenumber.txt filenumbersort.txt

#####
for NONSLIMFILEPATH in `ls $INPUTDIR/$DATASET/slim/*root`; do
    NONSLIMFILE="$( cut -d '/' -f 8 <<< "$NONSLIMFILEPATH" )" 
    NONSLIMFILE=`echo $NONSLIMFILE | sed 's/_f/#/g' `
    NONSLIMINDEX="$( cut -d '#' -f 2 <<< "$NONSLIMFILE" )" 
    NONSLIMINDEX=`echo $NONSLIMINDEX | cut -d "_" -f 1 `
    echo $NONSLIMINDEX >> filenumber.txt
done 

#####
sort -g filenumber.txt > filenumbersort.txt
NUMLINE=`wc -l filenumbersort.txt | awk '{print $1}'`
LASTFILENUM=`tail -n +$NUMLINE filenumbersort.txt`  
echo $LASTFILENUM

####
COUNTER=1
while [ $COUNTER -lt $(($LASTFILENUM)) ]; do
    echo The counter is $COUNTER
    if [ $(($LASTFILENUM-$COUNTER)) -lt $(($NFILEPERJOB)) ] 
    then 
        #echo $COUNTER to $(($LASTFILENUM))
        JobSubmit.csh ./RunOneJob.sh  $INPUTDIR/$DATASET/slim/ $RECOGNIZER $COUNTER $(($LASTFILENUM)) $ISDATA $LUMI
    else  
        #echo $COUNTER to $(($COUNTER+$NFILEPERJOB-1))  
        JobSubmit.csh ./RunOneJob.sh $INPUTDIR/$DATASET/slim/ $RECOGNIZER $COUNTER $(($COUNTER+$NFILEPERJOB-1)) $ISDATA $LUMI 
    fi

    let COUNTER=COUNTER+$NFILEPERJOB
done

#for file in `ls $INPUTDIR/$DATASET/*f*_*.root`; do
#    
#    FILE="$( cut -d '/' -f 7 <<< "$file" )" 
#    echo " [DEBUG] Doing " $FILE 
#    JobSubmit.csh ./RunOneJob.sh $INPUTDIR/$DATASET $OUTPUTDIR/$DATASET/slim $FILE  
#    #echo "JobSubmit.csh ./RunOneJob.sh $INPUTDIR/$DATASET $OUTPUTDIR/$DATASET $FILE"  
#
#done
