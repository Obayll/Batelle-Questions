<template>
  <div class="container">
    <h1>Input Echo App</h1>
    <input v-model="userInput" type="text" placeholder="Type something..." />
    <p>You typed: <strong>{{ userInput }}</strong></p>
  </div>
</template>

<script setup>
import { ref } from 'vue'

const userInput = ref('')
</script>

<style scoped>
.container {
  max-width: 500px;
  margin: 2rem auto;
  padding: 1rem;
  text-align: center;
  font-family: Arial, sans-serif;
}

input {
  padding: 0.5rem;
  width: 100%;
  font-size: 1rem;
  margin-bottom: 1rem;
}
</style>
