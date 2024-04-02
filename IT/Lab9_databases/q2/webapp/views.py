from django.shortcuts import render, redirect
from .forms import WorkForm
from .models import Company, Person, Address

def insert_work_data(request):
    if request.method == 'POST':
        form = WorkForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('home')
    else:
        form = WorkForm()
    return render(request, 'insert_work_data.html', {'form': form})

def get_employees_by_company(request):
    if request.method == 'POST':
        company_name = request.POST.get('company_name')
        company = Company.objects.filter(name=company_name).first()
        if company:
            employees = Person.objects.filter(company=company)
            return render(request, 'employees_by_company.html', {'employees': employees})
    return render(request, 'get_employees_by_company.html')
