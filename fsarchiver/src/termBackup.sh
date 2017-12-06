
#GPL 2.0

#termBackup.

#By team. jipuragi 
#github : https://github.com/sdong001/oss_hw4

#!/bin/bash

export LC_TIME=C

opt1_term=$1
opt2_day=$2
opt3_hour=$3

if [ "$opt1_term" = "--help" ]
then
	echo "====> termBackup.sh  <==="
	echo "*usage: ./termBackup.sh [<commands>, <option_day>, <option_hour>, <option_fsarchiver command>]"
	echo "<commands>"
	echo " * monthly : backup your dir or file system monthly"
	echo " * weekly : backup your dir or file system weekly"
	echo " * daily : backup your dir or file system daily"
	echo "<option>"
	echo " * option_day : day of your backup day"
	echo " * option_hour : hour of your backup hour in backup day"
	echo " * option_fsarchiver command : command of fsarchiver you want"
	echo "<examples>"
	echo " * termBackup.sh monthly 15 10"
	echo " * termBackup.sh weekly Sat 10"
	echo " * termBackup.sh daily 10"

	exit 0;
fi


pivotMonth=$(date +%m)
pivotWeek=$(date +%V)
pivotDay=$(date +%j)
IsBackup=false

echo -n "Input fsarchiver command : "
read opt4_command

echo "===>Scheduled backup info<==="
echo "Term : " $opt1_term
echo "Day or Hour : "  $opt2_day
echo "Hour : " $opt3_hour
echo "Command : " $opt4_command


while [ 1 ]
do
	echo "fsarchiver termbackup process running..."
	
	curMonth=$(date +%m)
	curSimpleDay=$(date +%d)
	curDay=$(date +%j)
	curDayTxt=$(date +%a)
	curHour=$(date +%H)
	curWeek=$(date +%V)

	case $opt1_term in
		monthly)
			if [ $curSimpleDay -eq $opt2_day -a $curHour -eq $opt3_hour -a "$IsBackup" = false ]; then
				echo $(date +\%Y\/%m\/%d\ %H\:%M) "monthly backup start!!"
				$opt4_command
				IsBackup=true
				pivotMonth=`expr $pivotMonth + 1`

				if [ $pivotMonth -eq 13 ]; then
					pivotMonth=1
				fi

			elif [ "$IsBackup" = true -a $pivotMonth -eq $curMonth ]; then
				IsBackup=false
			fi;;			

		weekly)
			if [ $curDayTxt = $opt2_day -a $curHour -eq $opt3_hour -a "$IsBackup" = false ]; then
				echo $(date +\%Y\/%m\/%d\ %H\:%M) "weekly backup start!!"
				$opt4_command
				IsBackup=true
				pivotWeek=`expr $pivotWeek + 1`

				if [ $pivotWeek -eq 54 ]; then
					pivotWeek=1
				fi

			elif [ "$IsBackup" = true -a $pivotWeek -eq $curWeek ]; then
				IsBackup=false
			fi;;

		daily)
			if [ $curHour -eq $opt2_day -a "$IsBackup" = false  ]; then
				echo $(date +\%Y\/%m\/%d\ %H\:%M) "daily backup start!!"
				$opt4_command
				IsBackup=true
				pivotDay=`expr $pivotDay + 1`

				if [ $pivotDay -eq 367 ]; then
					pivotDay=1
				fi
			elif [ "$IsBackup" = true -a $pivotDay -eq $curDay ]; then
				IsBackup=false
			fi;;

	esac
	sleep 60
done
