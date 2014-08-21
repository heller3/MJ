#!/bin/bash

INPUTDIR=/net/cms2/cms2r0/cfA
OUTPUTDIR=/net/cms26/cms26r0/jaehyeok/Fatjet
DATASET=$1

# make an output dir 
if [ ! -d "$OUTPUTDIR/$DATASET" ] 
then 
    echo " [DEBUG] Making directory $OUTPUTDIR/$DATASET " 
    mkdir -p $OUTPUTDIR/$DATASET 
fi 

for file in `ls $INPUTDIR/$DATASET/*.root`; do
    
    FILE="$( cut -d '/' -f 7 <<< "$file" )" 
    echo "[DEBUG] JobSubmit.csh ./RunOneJob.sh $INPUTDIR/$DATASET $OUTPUTDIR/$DATASET $FILE"  
    JobSubmit.csh ./RunOneJob.sh $INPUTDIR/$DATASET $OUTPUTDIR/$DATASET $FILE  

done
