from django.db import models

class Company(models.Model):
    name = models.CharField(max_length=255)

class Person(models.Model):
    name = models.CharField(max_length=255)
    company = models.ForeignKey(Company, on_delete=models.CASCADE)

class Address(models.Model):
    person = models.OneToOneField(Person, on_delete=models.CASCADE)
    street = models.CharField(max_length=255)
    city = models.CharField(max_length=255)
