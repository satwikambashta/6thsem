from django import forms
from .models import Company, Person, Address

class WorkForm(forms.ModelForm):
    class Meta:
        model = Person
        fields = ['name', 'company']
