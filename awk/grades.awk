#!/usr/bin/awk -f
BEGIN {
 FS = ":"
 print "Enter the Roll No:"
 getline roll_no < "-"
 print "Roll No\tName\tSubject\tMarks\tGrade"
 print "---------------------------------------------"
}
$1 == roll_no {
 name = $2
 print roll_no "\t" name "\tSubj1\t" $3 "\t" getGrade($3)
 print "\t\tSubj2\t" $4 "\t" " " getGrade($4)
 print "\t\tSubj3\t" $5 "\t" " " getGrade($5)
 print "\t\tSubj4\t" $6 "\t" " " getGrade($6)
 print "\t\tSubj5\t" $7 "\t" " " getGrade($7)
 print "---------------------------------------------"
}
function getGrade(mark) {
 if (mark >= 95) {
 return "O";
 } else if (mark >= 90) {
 return "A+";
 } else if (mark >= 85) {
 return "A";
 } else if (mark >= 80) {
 return "B+";
 } else if (mark >= 70) {
 return "B";
 } else if (mark >= 60) {
 return "C+";
 } else if (mark >= 50) {
 return "C";
 } else if (mark >= 40) {
 return "P";
 } else {
 return "F";
 }
}