from django import forms

class StudentForm(forms.Form):
    name = forms.CharField(label="Student Name", max_length=100)
    dob = forms.DateField(label="Date of Birth",widget=forms.DateInput(attrs={'type':'date'}))
    address = forms.CharField(label="Address",widget=forms.Textarea(attrs={'rows':3}))
    contact = forms.CharField(label="Contact Number",max_length=10)
    email = forms.EmailField(label="Email ID")

    #marks
    english = forms.IntegerField(label="English Marks",min_value=0,max_value=100)
    physics = forms.IntegerField(label="Physics marks",min_value=0,max_value=100)
    chemistry = forms.IntegerField(label="Chemistry Marks",min_value=0,max_value=100)