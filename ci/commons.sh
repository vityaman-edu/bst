#!/bin/sh

BLUE='\033[0;34m'
RED='\033[31m'
NC='\033[0m'

function message() {
    echo -e "${BLUE}[avl] $1${NC}"
}

function error() {
    echo -e "${RED}[avl] Error: $1${NC}"
}
