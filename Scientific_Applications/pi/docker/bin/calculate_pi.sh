#!/bin/bash
#############################
# Copyright (c) 2019 Red Hat
#
# Licensed under the Apache License, Version 2.0
# See LICENSE file for more information
#
# calculate_pi.sh
# Description: Calculate Pi number
#
#############################

FILEPATH=$(readlink -f $0)
BASEDIR=${FILEPATH%/*}

### FUNCTIONS
# Funtion that shows the common usage options
main_usage(){
    echo "# Usage: $0 [threads] [decimals]"
    echo "#"
    echo "# - example: $0 1 10"    
}


##### MAIN #####

main(){

  local threads="${1}"
  local decimals="${2}"

  .${BASEDIR}/chudnovsky-gmp-omp.bin "${threads}" "${decimals}"

  .${BASEDIR}/pi2txt.bin "${decimals}" omp-gmp-pi.dat pi_txt_file

  s3cmd put pi_txt_file s3://$S3_BUCKET

}

main "$@"

exit 0