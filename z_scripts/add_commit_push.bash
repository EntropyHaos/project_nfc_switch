function init(){
    local DIR;
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    local DIR_TO_ACT_ON;
    DIR_TO_ACT_ON=${DIR%*/z_scripts}
    cd $DIR_TO_ACT_ON;
    add_commit_push;
}

function add_commit_push(){
    # Get commit message.
    read -r -p "Enter commit message : " commit_message
    echo
    
    git add --all;
    git commit -m "$commit_message";
    git push --all;
}

init
