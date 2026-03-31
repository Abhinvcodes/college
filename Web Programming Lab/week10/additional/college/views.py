from django.shortcuts import render
from .models import Institute


def show_institutes(request):
    institutes_data = Institute.objects.all()
    return render(request, "institutes_list.html", {"institutes": institutes_data})
