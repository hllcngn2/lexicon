test1:
	gcc src/test1.c src/sentence.c src/lexic.c src/words.c src/tools.c -olexicon
vg:
	gcc src/verbalgroup.c src/lexic.c src/words.c src/tools.c -olexicon
clean:
	rm lexicon.exe lexicon.exe.stackdump
