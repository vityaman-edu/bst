#!/bin/sh

BLUE='\033[0;34m'
NC='\033[0m'

function message() {
    echo -e "${BLUE}[avl] $1${NC}"
}
