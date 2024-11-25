BEGIN {
    FS = ":"  # Set field separator to ":"
    # Print the header for the report
    print "Emp_No\tEmp_Name\tBasic_Salary\tDA\tHRA\tGross_Salary"
    print "-----------------------------------------------------------"
}

{
    emp_no = $1                 # Employee Number
    emp_name = $2               # Employee Name
    basic_salary = $3           # Basic Salary

    # Calculate DA (50% of Basic Salary) and HRA (30% of Basic Salary)
    da = basic_salary * 0.50
    hra = basic_salary * 0.30

    # Calculate Gross Salary
    gross_salary = basic_salary + da + hra

    # Print the result in the required format
    printf "%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n", emp_no, emp_name, basic_salary, da, hra, gross_salary
}
