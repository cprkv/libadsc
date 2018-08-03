cd build && cmake .. && make && \
(readelf --dyn-syms ../bin/tests | grep main$ && \
 readelf --dyn-syms ../bin/tests --wide | grep test_func_ | sort -k 8) \
| awk '{ print $2, $8 }' \
| ../bin/tests