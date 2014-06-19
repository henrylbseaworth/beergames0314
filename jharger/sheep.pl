#!/usr/bin/perl

if(scalar(@ARGV) != 2) {
    print "Usage: sheep.py <file> <key>\n\n";
	exit(1);
}

$filename = $ARGV[0];
$key = $ARGV[1];

{
    local $/ = undef;
    open FILE, "<", $filename or die $!;
    binmode FILE;
    
    $contents = <FILE>;

    close FILE;
}

$keylen = length($key);
$loc = 0;
$last = 0;
$count = 0;
open FILE, ">", $filename or die $!;

while($loc >= 0) {
    $loc = index($contents, $key, $last);
    if($loc >= 0) {
        $loc += $keylen;
        $count ++;
        print FILE substr($contents, $last, $loc - $last), "($count)";
        $last = $loc;
    }
}

print FILE substr($contents, $last);

close FILE;
