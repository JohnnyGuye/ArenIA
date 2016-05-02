lua %~dp0gendoc.lua %1 %~dp0

mkdir DocOutput
move %1.html .\DocOutput
del %1.md %1.tmp
copy %~dp0highlight.pack.js .\DocOutput
copy %~dp0github-markdown.css .\DocOutput
copy %~dp0styles\github.css .\DocOutput