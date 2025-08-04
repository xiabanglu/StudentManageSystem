@echo off
git add .
git commit -m "auto sync"
git push origin master
git push github master
pause