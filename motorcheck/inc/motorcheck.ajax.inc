<?php
/**
 * Motorcheck registration validate
 */
function motorcheck_registration_validate() {
  $data = drupal_get_query_parameters();

  if (!empty($data['reg']) && !empty($data['dep'])) {
    $params = [
      'reg' => $data['reg'],
      'current_odometer' => 10000,
      'annual_odometer_km' => 1000,
      'custom_valuation' => $data['dep'],
    ];

    $response = motorcheck_api_callback('/vehicle/custom/hyundaichallengefinancecalc', $params);
  }
  else {
    $response = [
      'success' => false,
      'error' => 'Invalid input data',
    ];
  }

  drupal_json_output($response);
}


/**
 * Get car info from Motorcheck API.
 */
function motorcheck_api_callback($call = '', $params) {
  $url = variable_get('motorcheck_url');
  $params['_username'] = variable_get('motorcheck_username');
  $params['_api_key'] = variable_get('motorcheck_api_key');
  $params['_end_user_ref'] = 'endUser';
  $params['format'] = 'json';

  $qry_str = http_build_query($params);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url . $call . '?' . $qry_str);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, 20);
  $response = trim(curl_exec($ch));

  // Check if there was an error in curl execution
  if (curl_errno($ch) > 0) {
    throw new Exception(curl_error($ch));
  }

  curl_close($ch);

  if (empty($response)) {
    throw new Exception('Response data could not be parsed.');
  }

  return $response;
}