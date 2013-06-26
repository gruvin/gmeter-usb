#!/usr/bin/awk -f
BEGIN {
  cmd = "/usr/bin/rrdtool fetch /root/trafficrrd/traffic.rrd AVERAGE -e now -s end-3h";
  while ((cmd | getline) > 0) {
    if ($2 ~ /^[0-9.e+]+$/) {
      hourlyTraffic += ($2 * 300);
    }
  }
  close(cmd);

  oneGig = 1073741824;
  if (hourlyTraffic  > 6 * oneGig) level = 3; # 6.0GB
  else if (hourlyTraffic > 2 * oneGig) level = 2; # 2.0GB 
  else if (hourlyTraffic > oneGig / 2) level = 1; # 0.5GB
  else level = 0;

  printf "Traffic: %4.2f MB over last 3 hours\n", hourlyTraffic / 1048576;
  printf "Level: %d\n", level;

  system("/root/trafficrrd/tMeterControl " level);

  exit;
} 

