from django.shortcuts import render

def feedback_view(request):
    context = {}
    
    if request.method == 'POST':
        # Retrieve data from the submitted form
        name = request.POST.get('student_name', '')
        sex = request.POST.get('sex', 'Male')
        
        # Determine the correct prefix based on the selected radio button
        prefix = "Mr." if sex == "Male" else "Miss."
        
        # Create the final message
        context['message'] = f"Thanks {prefix} {name} for your feedback."
        
    return render(request, 'course_feedback/feedback_form.html', context)