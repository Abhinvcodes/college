from django.shortcuts import render, redirect
from .models import Works, Lives

def dashboard(request):
    search_results = None
    searched_company = ""

    if request.method == 'POST':
        # 1. Handle Data Insertion
        if 'insert_work' in request.POST:
            p_name = request.POST.get('person_name')
            c_name = request.POST.get('company_name')
            sal = request.POST.get('salary')

            # Safeguard: Ensure the person exists in the LIVES table first
            # If they don't exist, we create a placeholder for them
            person, created = Lives.objects.get_or_create(
                person_name=p_name,
                defaults={'street': 'Unknown', 'city': 'Unknown'}
            )
            
            # Insert the record into WORKS
            Works.objects.create(person_name=person, company_name=c_name, salary=sal)
            return redirect('dashboard')

        # 2. Handle the Search Query
        elif 'search_company' in request.POST:
            searched_company = request.POST.get('search_company_name')
            # Fetch the works records and grab the associated LIVES data (city) at the same time
            search_results = Works.objects.filter(company_name__icontains=searched_company).select_related('person_name')

    return render(request, 'dashboard.html', {
        'results': search_results, 
        'company': searched_company
    })