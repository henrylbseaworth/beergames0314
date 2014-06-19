BEGIN {
	count = 0;
	FS = RS;
	keylen = length(key);
}
{
	where = 1;
	last = 1;
	do {
		str = substr($0, last);
		if(length(str) > 0) {
			where = match(substr($0, last), key);
		} else {
			where = 0;
		}
		if(where) {
			count ++;
			printf("%s(%d)", substr($0, last, where + (keylen-1)), count);
			last += where + (keylen-1);
		} else {
			print substr($0, last);
		}
	} while(where);
}
