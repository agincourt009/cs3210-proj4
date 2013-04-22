How to compile:
1.	Make sure java is installed on the machine running the code, specifically a version with javac i.e. OpenJDK. To install, type “yum install java-1.6.0-openjdk-devel.x86_64” into the terminal.
2.	When ssh’ing into factor, make sure to add -X like this:
ssh -X username@factor-3210.cc.gatech.edu
ssh -X factor014
3.	Compile the C code while in the src folder first by typing in “make”. 
4. 	Compile the java code by typing in:
javac -cp jna.jar User.java RelationshipList.java ControlList.java UserPanel.java ViewPanel.java AddPanel.java RelationshipPanel.java NewPanel.java LoginPanel.java MainPanel.java
5.	Mount fuse while in the example folder by typing:
./../src/p4_fs rootdir/ mountdir/
6. 	To run the program, type this command into the terminal: 
java -cp .:jna.jar MainPanel no
