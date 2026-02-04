from django import forms

class AdditionForm(forms.Form):
    number_1 = forms.IntegerField(label="First Number")
    number_2 = forms.IntegerField(label="Second Number")