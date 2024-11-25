{
    name = $1
    score1 = $2
    score2 = $3
    score3 = $4

    # Check if the student failed in any subject
    if (score1 < 40 || score2 < 40 || score3 < 40) {
        grade = "F"
    } 
    else {
        # Calculate overall grade based on total score
        total_score = score1 + score2 + score3
        average_score = total_score / 3

        if (average_score >= 90) {
            grade = "A"
        }
        else if (average_score >= 80) {
            grade = "B"
        }
        else if (average_score >= 70) {
            grade = "C"
        }
        else if (average_score >= 60) {
            grade = "D"
        }
        else {
            grade = "F"
        }
    }

    # Print the result
    print name, score1, score2, score3, grade
}
