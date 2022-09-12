cat 'wlist_all/wlist_match1.txt' | tr -dc '[:alnum:]\n\r'  > clear.txt | sort -u clear.txt >clear.txt
