BEGIN { 
    FS = " " 
} 
{ 
    total_marks = $NF + $(NF-1) + $(NF-2) 
    percentage = (total_marks / 300) * 100 
    if (percentage < 40) { 
        result = "Fail" 
    } else if (percentage >= 60 && percentage <= 65) { 
        result = "First Class" 
    } else if (percentage > 66) { 
        result = "Distinction" 
    } else { 
        result = "Pass" 
    } 
     
    print $0, "Total Marks:", total_marks, "Percentage:", percentage "%", "Result:", result 
} 