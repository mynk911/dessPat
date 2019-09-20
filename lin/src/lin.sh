#/!/bin/bash

# global variables
menu_choice=""
current_cd=""
title_file="title.cdb"
tracks="tracks.cdb"
temp_file=/tmp/cdb.$$
trap 'rm -f tmp_file' EXIT


# utilities
get_return() {
    echo -e "Press return \c"
    read x
    return 0
}

get_confirm() {
    echo -e "Are you sure ? \c"
    while true
    do
	read x
	case "$x" in
	    y | Y | yes | Yes | YES )
		return 0;;
	    n | N | no | No | NO )
		echo
		echo "cancelled"
		return 1;;
	    *) echo "Please enter yes or no" ;;
	esac
    done
}

# main menu function
set_menu_choice() {
    clear
    echo "Options :-"
    echo
    echo "    a) Add new CD"
    echo "    f) Find CD"
    echo "    c) Count the CDs and track in Catalog"
    if [ "$cdcatnum" != ""]; then
	echo "    l) List tracks on $cdtitle"
	echo "    r) Remove $cdtitle"
	echo "    u) updata track information for $cdtitle"
    fi
    echo "    q) quit"
    echo
    echo -e "Please enter choice and then return \c"
    read menu_choice
    return
}

insert_title() {
    echo $* >> $title_file
    return
}

insert_track() {
    echo $* >> $tracks_file
    return
}

add_record_tracks() {
    echo "Enter track information for this CD"
    echo "When no more tracks enter q"
    cdtrack=l
    cdttitle=""
    while [ "$cdttitle" != "q" ]
    do
	echo -e "Track $cdtrack, track file ? \c"
	read tmp
	cdttitle=${tmp%%,*}
	if [ $tmp != $cdttitle ]; then
	    echo "Sorry, no commas allowed"
	    continue
	fi
	if [ -n "$cdttitle" ]; then
	    if [ $cdttitle != "q" ]; then
		insert_track $cdcatnum,$cdtrack,$cdttitle
	    fi
	else
	    cdtrack=$((cdtrack-1))
	fi
	cdtrack=$((cdtrack+1))
    done
}

add_records() {
    echo -e "Enter catalog name \c"
    read tmp
    cdcatnum=${tmp%%,*}

    echo -e "Enter Title \c"
    read tmp
    cdtitle=${tmp%%,*}

    echo -e "Enter type \c"
    read tmp
    cdtype=${tmp%%,*}

    echo -e "Enter artist/composer"
    read tmp
    cdac=${tmp%%,*}

    echo about to add entry
    echo "$cdcatnum $cdtitle $cdtype $cdac"

    if get_confirm ; then
	insert_title $cdcatnum,$cdtitle,$cdtype,$cdac
	add_record_tracks
    else
	remove_records
    fi

    return
}

find_cd() {
    if [ "$1" = "n" ]; then
	asklist=n
    else
	asklist=y
    fi
    cdcatnum=""
    echo -e "Enter a string to to search for in CD Titles \c"
    read searchstr
    if [ "$searchstr" = "" ]; then
	return 0
    fi

    grep "$searchstr" $title_file > $temp_file

    set $(wc -l $temp_file)
    linesfound=$1

    case "$linesfound" in
	0) echo "Sorry, Nothing found"
	   get_return
	   return 0
	   ;;
	1) ;;
	2) echo "Sorry, Not unique"
	   echo "found the following"
	   cat $temp_file
	   get_return
	   return 0
    esac

    Old_IFS="$IFS"
    IFS=","
    read cdcatnum cdtitle cdtype cdac < $temp_file
    IFS="$Old_IFS"

    if [ -z "$cdcatnum" ]; then
	echo "Sorry, could not extract catalog field from $temp_file"
	get_return
	return 0
    fi

    echo
    echo Catalog number: $cdcatnum
    echo Title : $cdtitle
    echo Type : $cdtype
    echo Artist/Composer : $cdac
    echo
    get_return

    if [ "$ask_list" = "y" ]; then
	echo -e "View Tracks for this CD ? \c"
	read x
	
	
}
