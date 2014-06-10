beergames0313
=============

The Week of June 9, 2014 beer games (Numero 3).

Due: Tuesday, June 17 as close to 11:00 pm MST as possible.

Challenge
-----
Develop a program that servers as many clients as possible. New clients will continuously attempt to connect to your server. The connections will be TCP/IP. Each client will expect to be served a given file (not exceeding 4KB). Once it is served the file it will expect to be served it again (and continuoysly until something is beaten to death). 

Example
-----
Forthcoming.

## Beer Games Rules (Preliminary)

### Programs
Contestants can enter any number of programs. Programs can use any language, libraries, or dependencies. The manner in which programs will be evaluated is decided upon before the due date (or after). 

### Submissions
Create your folder in the root directory of the repository. You can choose anything as its name except "dasboot" (that's where we'll keep all the tests and benchmarking stuff). 

For those not fammiliar with Git, if I wanted to submit my program called SortingIPAs.c I could use the following procedure:

```bash
git clone https://github.com/henrylbseaworth/beergames0314.git
cd beergames0314

#create my folder/handle and copy in my submission
mkdir -p MyFoldr && cp SortingIPAs.c MyFoldr/

git add baconsSubs/SortingIPAs.c 	#add my submission to be tracked 
git commit -m "added my submission yay!"    #commit this change to the stage
git push -u orign master    #push my changes to the repo
```

Another Git-tip: *it's a good idea to always pull before making changes and before pushing changes. For example if you run ```bash git pull``` before editing/commiting you'll save a bit of headeach if your changes affect other people's changes.  This shouldn't be an issue here but since we're all trying to learn ;D*


### Rewards
By tradition, the winner of the challenge picks a celebration venue (bar). All contestants that complete the challenge are invited to the celebration and are not obligated to buy the winner(s) anything. 

