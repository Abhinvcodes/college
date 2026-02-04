from django.shortcuts import render
from .forms import PromotionForm
from datetime import date

def promotion_check_view(request):
    result = ""
    form = PromotionForm()

    if request.method == "POST":
        form = PromotionForm(request.POST)
        if form.is_valid():
            doj = form.cleaned_data['date_of_joining']
            today = date.today()
            
            # Calculate years of experience
            # Logic: (Current Year - Joining Year)
            experience = today.year - doj.year - ((today.month, today.day) < (doj.month, doj.day))
            
            if experience >= 5:
                result = "YES"
            else:
                result = "NO"

    return render(request, 'employees/check.html', {
        'form': form,
        'result': result
    })