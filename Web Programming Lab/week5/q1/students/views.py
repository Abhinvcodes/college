from django.shortcuts import render
from .forms import StudentForm

def student_form_view(request):
    display_data = ""
    percentage = 0
    form = StudentForm()

    if request.method == "POST":
        form = StudentForm(request.POST)
        if form.is_valid():
            data = form.cleaned_data
            #calculate percentage
            total = data['english'] + data['physics'] + data['chemistry']
            percentage = round((total/300) * 100, 2)

            #format data for the TextArea
            display_data = (
                f"Name {data['name']}\n"
                f"DOB: {data['dob']}\n"
                f"Address: {data['address']}\n"
                f"Contact: {data['contact']}\n"
                f"Email: {data['email']}\n"
                f"Marks: Eng: {data['english']}, Phys: {data['physics']}, Chem: {data['chemistry']}\n"
            )
    return render(request, 'students/form.html',{
        'form':form,
        'display_data':display_data,
        'percentage':percentage
    })