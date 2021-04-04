# os-s20: Project 0: Bootloader

The source files contain the Tasks to be implemented by you along with some helpful hints.

Each student has his/her own personal private repository. You may add/commit/push as you please during the completion of the project.

## Submission
To submit the project, you will create and push a tag from the latest commit will ALL of your code. If there are any additional information you would like us to know, please update this readme with the same.

### To submit:
1. Commit and Push ALL your code
```
$ git add <LIST_OF_UPDATED_FILES>
$ git commit -m "<COMMENT>"
$ git push origin project0
```
2. Create a tag named `v0`.
```
$ git tag -a v0 -m "Submission for project 0."
```

3. Push the tag:
```
$ git push origin v0
```

### To Re-submit:
To re-submit you will have to forcefully update the tag and (if already pushed) forcefully push the tag.

1. Make necessary changes, Commit and Push ALL you changes.
```
$ git add <LIST_OF_UPDATED_FILES>
$ git commit -m "<COMMENT>"
$ git push origin project0
```

2. Update the tag:
```
$ git tag -a -f v0 -m "Resubmission for project 0."
```

3. Forcefully push the tag:
```
$ git push -f origin v0
```


## Anything we should know???
To execute the boot files simply run the script.sh provided in the folder "./script.h" and then finally run simulator.sh to run the bootloader.
