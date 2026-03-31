from django.urls import path
from . import views

urlpatterns = [
    path('', views.directory_index, name='directory_index'),
    path('go/<int:page_id>/', views.go_to_page, name='go_to_page'),
]