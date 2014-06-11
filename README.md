beergames0214
=============

Week of June 2, 2014 beer games.

Due: Monday, June 9 as close to 4:35 pm MST as possible.

Challenge
-----
Develop a program that takes two inputs, a "text file" and a "key" (the key and text file can be any ascii string). The program searches the text file for the key. If the key is found the program inserts the number of occurrences of the key up to that point in the document directly after each key and the number is surrounded by parentheses (because the l33t team really likes them). The changes will be made in-place e.g. there is no "output" file, the changes are made to the original text. 

A script (provided) will benchmark the performance of each program. The author of fasterst program wins. 

Example
-----
We have a file "example-test.txt". The first part of this file looks like:
	
	    Non eram nescius, Brute, cum, quae summis ingeniis exquisitaque doctrina philosophi Graeco sermone tractavissent, ea Latinis litteris mandaremus, fore ut hic noster labor in varias reprehensiones incurreret. 
a
The example program, drunkensub, will operate like this: 

	    ./drunkensub example-test.txt ae
	    
After completion  the text file, "example-test.txt", will look like:

	    Non eram nescius, Brute, cum, quae(1) summis ingeniis exquisitaque doctrina philosophi Grae(2)co sermone tractavissent, ea Latinis litteris mandaremus, fore ut hic noster labor in varias reprehensiones incurreret. 

Finally, on the due date, all programs will be evaluated with the following parameters.
1. Programs will be benchmarked with the same (provided) script. The script runs each of your programs (specified in the programlist file, see Submissions).
2. Text files will be small enough to fit in memory but quite large.
3. Keys will be smaller than text files but will be pretty small.
4. The program that finishes in the quickest time wins.

## General Beer Games Rules (Preliminary)

You can use any languages/libraries/hax so long as it works on the test machine (talk to the l33t team for which are installed/adding more). Whoever completes the program is invited to a venue to drink beer. Whoever "wins" the challenge chooses the venue and gets a secret surpise gift, decided upon by the l33t team. 

This is a special Beer Games because winners will get a beer purchased by the l33t team. If you're under 21 then you'll still get a beer, but you may not be able to drink it.

### Programs
Contestants can enter any number of programs. Programs can use any language, libraries, or other programs on the test machine. The programs will be evaluated on ONE agreed upon machine. 

### Submissions
Make a folder in the root directory of the repository. The name of this folder is your handle, you can choose anything except "dasboot" (that's where we'll keep all the tests and benchmarking stuff). Put all your submissions in your folder. In your folder you also need a file called "programlist" that conatins a list of all your programs. Here's an example programlist file:

        ./mysubmittion.py  #for a script that has #!/usr/local/bin/python
        ruby myothersubmission.rb    #for a script that doesn't have #!/usr/local/bin/ruby
        ./mycprogram.out    #a compiled program

Each participant will be given access to the test server before they have to submit. Talk to the l33t team for details.

For those not fammiliar with Git, if I wanted to submit my program called SortingIPAs.sh I could use the following procedure:

```bash
git clone https://github.com/henrylbseaworth/beergames0214.git
cd beergames0214

#create my folder/handle and copy in my submission
mkdir -p baconsSubs && cp SortingIPAs.sh baconsSubs/

git add baconsSubs/SortingIPAs.sh #add my submission to be tracked 
git commit -m "added my submission yay!"    #commit this change to the stage
git push -u orign master    #push my changes to the repo
```

Another Git-tip: *it's a good idea to always pull before making changes and before pushing changes. For example if you run ```bash git pull``` before editing/commiting you'll save a bit of headeach if your changes affect other people's changes.  This shouldn't be an issue here but since we're all trying to learn ;D*


About
-----
The Beer Games are a friendly challenge meant to ~~celebreate drinking~~ keep programmers' minds sharp. They're also a good oportunity to teach yourself something new and look at other developer's solutions. 


