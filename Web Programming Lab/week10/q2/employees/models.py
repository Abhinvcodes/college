from django.db import models

class Lives(models.Model):
    person_name = models.CharField(max_length=100, primary_key=True)
    street = models.CharField(max_length=150)
    city = models.CharField(max_length=100)

    def __str__(self):
        return self.person_name

class Works(models.Model):
    # This creates a relational link between the two tables
    person_name = models.ForeignKey(Lives, on_delete=models.CASCADE)
    company_name = models.CharField(max_length=100)
    salary = models.DecimalField(max_digits=10, decimal_places=2)

    def __str__(self):
        return f"{self.person_name.person_name} - {self.company_name}"