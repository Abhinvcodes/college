from django.urls import path
from . import views

urlpatterns = [
    path('',views.add_numbers,name='add_numbers'),
]