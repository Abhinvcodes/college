from django.shortcuts import render, redirect

def page1(request):
    if request.method == 'POST':
        # 1. Get data from the form
        name = request.POST.get('name')
        total_marks = request.POST.get('total_marks')

        # 2. Store the data in Django sessions
        request.session['student_name'] = name
        request.session['total_marks'] = total_marks

        # 3. Redirect to Page 2
        return redirect('page2')

    return render(request, 'calculator/page1.html')

def page2(request):
    # 1. Retrieve the data from the session
    name = request.session.get('student_name', 'Unknown')
    total_marks = request.session.get('total_marks', 0)

    # 2. Calculate CGPA (Total Marks / 50)
    try:
        cgpa = float(total_marks) / 50
        # Format the number so it shows "9" instead of "9.0" to match your image
        if cgpa.is_integer():
            cgpa = int(cgpa)
    except ValueError:
        cgpa = 0

    # 3. Pass data to the template
    context = {
        'name': name,
        'cgpa': cgpa
    }
    
    return render(request, 'calculator/page2.html', context)