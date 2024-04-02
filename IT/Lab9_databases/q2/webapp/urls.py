from django.urls import path
from . import views

urlpatterns = [
    path('insert_work_data/', views.insert_work_data, name='insert_work_data'),
    path('get_employees_by_company/', views.get_employees_by_company, name='get_employees_by_company'),
]
