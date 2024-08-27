
$ok=true
if [[ ! -f $1 || $1 -ot "$1.cpp" ]]; then
    g++ $1.cpp -Wall -Wconversion -Wfatal-errors -g -std=c++17 -o $1
    $ok=false
fi

if [[ $ok = true ]]; then
    ./$1
fi
