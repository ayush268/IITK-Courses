sed '12,14d' qn.c
sed '11,15c hello' qn.c
sed 's/$/axxa/g' qn.c 
sed 's/;$/,/g' > qn1.c
sed '/,$/ s/,$/;/g' qn1.c
sed 's/^/\/\*comment\*\//g' qn.c
sed '11,14s/^/\/\*comment\*\//' qn.c
sed 's/$/jhfj/11,15' parse.awk
sed  's/^[[:space:]]*if[[:space:]]*/IF/g' qn.c
sed  '/^[[:space:]]*if[[:space:]]*/ s/if/IF/g' qn.c
