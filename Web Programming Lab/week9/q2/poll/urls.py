from django.urls import path
from . import views

urlpatterns = [
    path('', views.vote_view, name='vote'),
]