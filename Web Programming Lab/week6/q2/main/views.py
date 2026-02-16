from django.shortcuts import render

def magazine_view(request):
    return render(request, 'magazine.html')