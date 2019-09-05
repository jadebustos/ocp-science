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
    echo "# Usage: $0 [threads] [pidigits]"
    echo "#"
    echo "# - example: $0 1 10"    
}


##### MAIN #####

main(){

  local threads="${1}"
  local pidigits="${2}"
  local timestamp=$(date +%Y%m%d%H%M%S)

  .${BASEDIR}/chudnovsky-gmp-omp.bin "${threads}" "${pidigits}"

  .${BASEDIR}/pi2txt.bin "${pidigits}" omp-gmp-pi.dat "${BASEDIR}/pi_txt_file.${timestamp}"

  s3cmd put "${BASEDIR}/pi_txt_file.${timestamp}" s3://$S3_BUCKET

}

main "$@"

exit 0
