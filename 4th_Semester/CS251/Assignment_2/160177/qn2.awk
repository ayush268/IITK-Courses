#!/usr/bin/awk -f

function timetaken(initial, final) {           # Function to calculate time difference
  temp = split(initial, x, ":")
  temp = split(final, y, ":")
  time = ((y[1]-x[1])*3600) + ((y[2]-x[2])*60) + (y[3]-x[3])
  return time
}

BEGIN {                          # Basic Declarations
  initial_timestamp[""] = 0;
  packets[""] = 0;
  final_timestamp[""] = 0;
  data[""] = 0;
  data_packets[""] = 0;
  retrans[""] = 0;
  union[""][""] = 0;
}

{
  IP1 = $3;
  temp = sub("\.[0-9]+$", "", IP1);             # Evaluating sender IP and Port
  PORT1 = a[split($3, a, "\.")];
  IP2 = $5;
  temp = sub("\.[0-9]+:$", "", IP2);            # Evaluating receiver IP and Port
  PORT2 = a[split($5, a, "\.")];
  temp = sub(":", "", PORT2);
  con_name = IP1 ":" PORT1 "to" IP2 ":" PORT2;      # Format for storing
  if (initial_timestamp[con_name] == 0) {
    initial_timestamp[con_name] = $1;
  }
  final_timestamp[con_name] = $1;                 # Timestamps for throughput
  if (!packets[con_name]) {                       # Initialization
    if ($NF != 0) {
      n = a[split($9, a, ":")];
      temp = sub(",$", "", n);
      m = a[1];
      union[1][1] = int(m+1);
      union[1][2] = int(n);
    }
    else {
      union[1][1] = 0;
      union[1][2] = 0;
    }
    retrans[con_name] = 0;
  }
  packets[con_name]++;
  len = $NF;
  if ($9 ~ /:/) {                                # Basically if len > 0
    seq2 = a[split($9, a, ":")];
    temp = sub(",$", "", seq2);
    seq1 = a[1];
    data_packets[con_name]++;
    n = a[split($9, a, ":")];
    temp = sub(",$", "", n);
    m = a[1]+1;
    if (packets[con_name]){
      flagr = 0;
      for (i in union) {
        left = union[i][1];
        right = union[i][2];
        if (m >= left && m <= right) {
          if (n >= left && n <= right) {
            flagr = 1;
            retrans[con_name] += 1+n-m;
            break;
          }
          else {
            retrans[con_name] += 1+right-m;
            m = right+1;
          }
        }
        else if (n >= left && n <= right) {
          if (m >= left && m <= right) {
            flagr = 1;
            retrans[con_name] += 1+n-m;
            break;
          }
          else {
            retrans[con_name] += 1+n-left;
            n=left-1;
          }
        }
      }
      if (flagr == 0 && m && n) {
        temp_len = length(union)+1;
        union[temp_len][1] = int(m);
        union[temp_len][2] = int(n);
      }
    }
  }

  data[con_name] += len;
}

END {
  for (i in packets) {
    if (packets[i] == 0) {continue;}
    temp=split(i, conn, "to");
    j = conn[2] "to" conn[1];
    done = i "and" j;
    print "Connection (A=" conn[1] ", B=" conn[2] ")";
    print "------------------------------------------";
    xput1 = (data[i] - retrans[i]) / timetaken(initial_timestamp[i], final_timestamp[i]);
    xput2 = (data[j] - retrans[j]) / timetaken(initial_timestamp[j], final_timestamp[j]);
    data_packets[i] += 0;
    data_packets[j] += 0;
    retrans[i] += 0;
    retrans[j] += 0;
    printf "A-->B #packets=" packets[i] ", #datapackets=" data_packets[i] ", #bytes=" data[i] ", #retrans=" retrans[i] ", xput=%d bytes/sec\n", xput1
    printf "B-->A #packets=" packets[j] ", #datapackets=" data_packets[j] ", #bytes=" data[j] ", #retrans=" retrans[j] ", xput=%d bytes/sec\n", xput2
    print "";
    packets[i] = 0;
    packets[j] = 0;
  }
}
