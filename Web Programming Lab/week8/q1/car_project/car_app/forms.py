from django import forms


class CarForm(forms.Form):
    # Define the choices for the dropdown list
    MANUFACTURER_CHOICES = [
        ("Toyota", "Toyota"),
        ("Honda", "Honda"),
        ("Ford", "Ford"),
        ("BMW", "BMW"),
        ("Tata", "Tata"),
        ("Mahindra", "Mahindra"),
    ]

    # Dropdown list for the manufacturer
    manufacturer = forms.ChoiceField(
        choices=MANUFACTURER_CHOICES, label="Car Manufacturer"
    )

    # Text box for the model name
    model_name = forms.CharField(max_length=100, label="Model Name")
