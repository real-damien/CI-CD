#!/bin/bash

      if scp cat/s21_cat grep/s21_grep server@192.168.0.11:/usr/local/bin ; then
        echo -e "Successfully copied artifacts to /usr/local/bin"
      else
        echo -e "Failed to copy artifacts"
        exit 1
      fi

      