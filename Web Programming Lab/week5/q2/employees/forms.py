from django import forms

class PromotionForm(forms.Form):
    # Example Employee IDs for the dropdown
    EMPLOYEE_CHOICES = [
        ('E101', 'E101'),
        ('E102', 'E102'),
        ('E103', 'E103'),
        ('E104', 'E104'),
    ]
    
    employee_id = forms.ChoiceField(choices=EMPLOYEE_CHOICES, label="Select Employee ID")
    date_of_joining = forms.DateField(
        label="Date of Joining",
        widget=forms.DateInput(attrs={'type': 'date'})
    )