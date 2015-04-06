echo "bt_std===================================================="
./bt_std |awk '{print "addr2line -s "$3" -e bt_std"}'>t.sh;. t.sh;
echo "bt===================================================="
./bt|awk '{print "addr2line -s "$3" -e bt"}'>t.sh;. t.sh;
echo "bt34===================================================="
./bt34|awk '{print "addr2line -s "$3" -e bt34"}'>t.sh;. t.sh;rm -f t.sh
