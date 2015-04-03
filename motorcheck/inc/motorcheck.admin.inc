<?php

/**
 * Implements hook_form().
 */
function motorcheck_config_form($form, &$form_state) {

  $form['connection'] = [
    '#type' => 'fieldset',
    '#title' => t('Connection detail'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $form['connection']['motorcheck_url'] = [
    '#type' => 'textfield',
    '#title' => t('Motorcheck API url:'),
    '#default_value' => variable_get('motorcheck_url'),
    '#size' => 80,
    '#maxlength' => 80,
    '#element_validate' => ['motorcheck_validate_url'],
    '#description' => t('Url of Motorcheck web service.'),
    '#required' => TRUE,
  ];

  $form['connection']['motorcheck_username'] = [
    '#type' => 'textfield',
    '#title' => t('Username:'),
    '#default_value' => variable_get('motorcheck_username'),
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('Username used for authentication with Motorcheck API.'),
    '#required' => TRUE,
  ];

  $form['connection']['motorcheck_api_key'] = [
    '#type' => 'textfield',
    '#title' => t('API key:'),
    '#default_value' => variable_get('motorcheck_api_key'),
    '#size' => 40,
    '#maxlength' => 40,
    '#description' => t('Api key used for authentication with Motorcheck API.'),
    '#required' => TRUE,
  ];

//  $form['caching'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Caching'),
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form['caching']['motorcheck_cache'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Cache responses from Motorcheck'),
//    '#default_value' => variable_get('motorcheck_cache', 0),
//  );
//
//  $period = drupal_map_assoc(array(0, 60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval');
//  $period[0] = '<' . t('none') . '>';
//  $form['caching']['motorcheck_cache_lifetime'] = array(
//    '#type' => 'select',
//    '#title' => t('Cache lifetime'),
//    '#default_value' => variable_get('motorcheck_cache_lifetime', 0),
//    '#options' => $period,
//    '#description' => t('Cached pages will not be re-created until at least this much time has elapsed.')
//  );
//
//  $form['error'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Error reporting'),
//    '#collapsible' => TRUE,
//    '#collapsed' => FALSE,
//  );
//
//  $form['error']['motorcheck_error_reporting'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Log error messages to Drupal log.'),
//    '#default_value' => variable_get('motorcheck_error_reporting', 1),
//  );

  return system_settings_form($form);
}

/**
 * Validate input to be valid url.
 *
 * @param $element
 * @param $form_state
 * @param $form
 */
function motorcheck_validate_url($element, &$form_state, $form) {
  if (!valid_url($element['#value'], TRUE)) {
    form_error($element, t('Url is not valid.'));
  }
}