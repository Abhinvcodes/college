from django.urls import path
from . import views

urlpatterns = [
    path('', views.home_view, name='home'),
    path('bill/', views.bill_view, name='produce_bill'),
]